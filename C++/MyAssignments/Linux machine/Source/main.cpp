//
//  main.cpp
//  Linux machine
//
//  Created by Belousov Ilya on 27.08.21.
//

//Есть linux машина с неправильным временем.
//У этой машины есть доступ в интернет.
//Нужно написать программу, которая бы устанавливала время правильно с помощью http запроса на веб-сервер google.
//В заголовках HTTP ответа есть поле ‘date’; надо его распарсить и установить время на linux машине с помощью системных функций.
//После того, как время установлено, программа должна делать https запрос на https://example.com , вывести на консоль данные, которые отдаст сервер.
//Логи должны писаться в отдельный файл, который можно задать через параметр командной строки либо через переменную окружения.
//Так же они должны записываться из отдельного потока (т.е. функция логирования должна передавать отформатированное сообщение другому потоку, который уже будет записывать это сообщение в файл).
//Заметки:
//Можно использовать libcurl для HTTPS запроса;
//http запрос сделать вручную;
//Время по-умолчанию на нашей машине очень неправильное (например 1 января 2000 года);
//Ясные и понятные логи, чтобы в случае чего можно было быстро диагностировать проблему/исправить;
//Должны быть доступны все файлы для сборки (Makefile например).
//Если нужны какие-то сторонние библиотеки - они должны быть описаны в README файле с инструкцией, как их установить;
//Не должно быть никаких утечек/оставленных открытых дескрипторов;
//Код должен быть на github'e (либо другом хостинге).
//Желательно пушить код на github после каждой сделанной фичи, чтобы была видна история/развитие (а не чтобы весь проект одним коммитом туда залит);
//Код должен быть оформлен в одном стиле;
//Пример запроса/ответа можно посмотреть с помощью команды 'curl -v http://google.com'

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sys/types.h>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>
using namespace::std;

// Performs an HTTP GET and prints the response
int main(int argc, char** argv) {
    try {
        auto const host = "www.google.com";
        auto const port = "80";
        auto const target = "/";
        auto const version = 11;
        
        net::io_context ioc; // функция ввода и вывода
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);
        
        auto const results = resolver.resolve(host, port); // создает запрос к которому мы хотим подключиться
        // Установите соединение с IP-адресом, который мы получаем в результате поиска.
        stream.connect(results);
        
        // Настройка сообщения HTTP-запроса GET
        http::request<http::string_body> req;
//        req.
        req.set(http::field::host, host);
        req.method(http::verb::get);
        req.version(version);
        req.target(target);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
//        req.version(11);
        
        // Send the HTTP request to the remote host
        http::write(stream, req);
        
        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;
        
        // Declare a container to hold the response
        http::response<http::dynamic_body> res;
        
        // Receive the HTTP response
        http::read(stream, buffer, res);
        
        // Write the message to standard out
        std::cout << res << std::endl;
        
        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        
        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};
        
        // If we get here then the connection is closed gracefully
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
