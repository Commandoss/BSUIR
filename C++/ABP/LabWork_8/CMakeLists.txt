cmake_minimum_required(VERSION 3.22)
project(LabWork_8)

set(CMAKE_CXX_STANDARD 20)

#include_directories(${PROJECT_SOURCE_DIR}/ffmpeg/include)

#set(FFMPEG_DIRS
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/ac3_parser.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/adts_parser.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/avcodec.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/avdct.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/avfft.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/bsf.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/codec_desc.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/codec_id.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/codec_par.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/codec.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/d3d11va.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/defs.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/dirac.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/dv_profile.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/dxva2.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/jni.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/mediacodec.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/packet.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/qsv.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/vdpau.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/videotoolbox.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/vorbis_parser.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavcodec/xvmc.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavdevice/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavdevice/avdevice.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavfilter/avfilter.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavfilter/buffersink.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavfilter/buffersrc.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavfilter/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavformat/avformat.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavformat/avio.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavformat/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/adler32.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/aes_ctr.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/aes.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/attributes.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/audio_fifo.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/avassert.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/avconfig.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/avstring.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/avutil.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/base64.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/blowfish.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/bprint.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/bswap.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/buffer.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/camellia.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/cast5.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/channel_layout.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/common.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/cpu.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/crc.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/des.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/detection_bbox.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/dict.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/display.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/dovi_meta.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/downmix_info.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/encryption_info.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/error.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/eval.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/ffversion.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/fifo.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/file.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/film_grain_params.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/frame.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hash.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hdr_dynamic_metadata.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hmac.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_cuda.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_d3d11va.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_drm.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_dxva2.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_mediacodec.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_opencl.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_qsv.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_vaapi.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_vdpau.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_videotoolbox.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext_vulkan.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/hwcontext.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/imgutils.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/intfloat.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/intreadwrite.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/lfg.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/log.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/lzo.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/macros.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/mastering_display_metadata.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/mathematics.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/md5.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/mem.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/motion_vector.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/murmur3.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/opt.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/parseutils.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/pixdesc.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/pixelutils.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/pixfmt.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/random_seed.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/rational.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/rc4.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/replaygain.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/ripemd.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/samplefmt.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/sha.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/sha512.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/spherical.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/stereo3d.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/tea.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/threadmessage.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/time.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/timecode.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/timestamp.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/tree.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/twofish.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/tx.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/video_enc_params.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libavutil/xtea.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libpostproc/postprocess.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libpostproc/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libswresample/swresample.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libswresample/version.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libswscale/swscale.h
#        ${PROJECT_SOURCE_DIR}/ffmpeg/include/libswscale/version.h
#        )
#
#include_directories(${FFMPEG_DIRS})
#link_directories(${FFMPEG_DIRS})

add_executable(main
        ffmpeg/include/libavcodec/ac3_parser.h
        ffmpeg/include/libavcodec/adts_parser.h
        ffmpeg/include/libavcodec/avcodec.h
        ffmpeg/include/libavcodec/avdct.h
        ffmpeg/include/libavcodec/avfft.h
        ffmpeg/include/libavcodec/bsf.h
        ffmpeg/include/libavcodec/codec_desc.h
        ffmpeg/include/libavcodec/codec_id.h
        ffmpeg/include/libavcodec/codec_par.h
        ffmpeg/include/libavcodec/codec.h
        ffmpeg/include/libavcodec/d3d11va.h
        ffmpeg/include/libavcodec/defs.h
        ffmpeg/include/libavcodec/dirac.h
        ffmpeg/include/libavcodec/dv_profile.h
        ffmpeg/include/libavcodec/dxva2.h
        ffmpeg/include/libavcodec/jni.h
        ffmpeg/include/libavcodec/mediacodec.h
        ffmpeg/include/libavcodec/packet.h
        ffmpeg/include/libavcodec/qsv.h
        ffmpeg/include/libavcodec/vdpau.h
        ffmpeg/include/libavcodec/version.h
        ffmpeg/include/libavcodec/videotoolbox.h
        ffmpeg/include/libavcodec/vorbis_parser.h
        ffmpeg/include/libavcodec/xvmc.h
        ffmpeg/include/libavdevice/version.h
        ffmpeg/include/libavdevice/avdevice.h
        ffmpeg/include/libavfilter/avfilter.h
        ffmpeg/include/libavfilter/buffersink.h
        ffmpeg/include/libavfilter/buffersrc.h
        ffmpeg/include/libavfilter/version.h
        ffmpeg/include/libavformat/avformat.h
        ffmpeg/include/libavformat/avio.h
        ffmpeg/include/libavformat/version.h
        ffmpeg/include/libavutil/adler32.h
        ffmpeg/include/libavutil/aes_ctr.h
        ffmpeg/include/libavutil/aes.h
        ffmpeg/include/libavutil/attributes.h
        ffmpeg/include/libavutil/audio_fifo.h
        ffmpeg/include/libavutil/avassert.h
        ffmpeg/include/libavutil/avconfig.h
        ffmpeg/include/libavutil/avstring.h
        ffmpeg/include/libavutil/avutil.h
        ffmpeg/include/libavutil/base64.h
        ffmpeg/include/libavutil/blowfish.h
        ffmpeg/include/libavutil/bprint.h
        ffmpeg/include/libavutil/bswap.h
        ffmpeg/include/libavutil/buffer.h
        ffmpeg/include/libavutil/camellia.h
        ffmpeg/include/libavutil/cast5.h
        ffmpeg/include/libavutil/channel_layout.h
        ffmpeg/include/libavutil/common.h
        ffmpeg/include/libavutil/cpu.h
        ffmpeg/include/libavutil/crc.h
        ffmpeg/include/libavutil/des.h
        ffmpeg/include/libavutil/detection_bbox.h
        ffmpeg/include/libavutil/dict.h
        ffmpeg/include/libavutil/display.h
        ffmpeg/include/libavutil/dovi_meta.h
        ffmpeg/include/libavutil/downmix_info.h
        ffmpeg/include/libavutil/encryption_info.h
        ffmpeg/include/libavutil/error.h
        ffmpeg/include/libavutil/eval.h
        ffmpeg/include/libavutil/ffversion.h
        ffmpeg/include/libavutil/fifo.h
        ffmpeg/include/libavutil/file.h
        ffmpeg/include/libavutil/film_grain_params.h
        ffmpeg/include/libavutil/frame.h
        ffmpeg/include/libavutil/hash.h
        ffmpeg/include/libavutil/hdr_dynamic_metadata.h
        ffmpeg/include/libavutil/hmac.h
        ffmpeg/include/libavutil/hwcontext_cuda.h
        ffmpeg/include/libavutil/hwcontext_d3d11va.h
        ffmpeg/include/libavutil/hwcontext_drm.h
        ffmpeg/include/libavutil/hwcontext_dxva2.h
        ffmpeg/include/libavutil/hwcontext_mediacodec.h
        ffmpeg/include/libavutil/hwcontext_opencl.h
        ffmpeg/include/libavutil/hwcontext_qsv.h
        ffmpeg/include/libavutil/hwcontext_vaapi.h
        ffmpeg/include/libavutil/hwcontext_vdpau.h
        ffmpeg/include/libavutil/hwcontext_videotoolbox.h
        ffmpeg/include/libavutil/hwcontext_vulkan.h
        ffmpeg/include/libavutil/hwcontext.h
        ffmpeg/include/libavutil/imgutils.h
        ffmpeg/include/libavutil/intfloat.h
        ffmpeg/include/libavutil/intreadwrite.h
        ffmpeg/include/libavutil/lfg.h
        ffmpeg/include/libavutil/log.h
        ffmpeg/include/libavutil/lzo.h
        ffmpeg/include/libavutil/macros.h
        ffmpeg/include/libavutil/mastering_display_metadata.h
        ffmpeg/include/libavutil/mathematics.h
        ffmpeg/include/libavutil/md5.h
        ffmpeg/include/libavutil/mem.h
        ffmpeg/include/libavutil/motion_vector.h
        ffmpeg/include/libavutil/murmur3.h
        ffmpeg/include/libavutil/opt.h
        ffmpeg/include/libavutil/parseutils.h
        ffmpeg/include/libavutil/pixdesc.h
        ffmpeg/include/libavutil/pixelutils.h
        ffmpeg/include/libavutil/pixfmt.h
        ffmpeg/include/libavutil/random_seed.h
        ffmpeg/include/libavutil/rational.h
        ffmpeg/include/libavutil/rc4.h
        ffmpeg/include/libavutil/replaygain.h
        ffmpeg/include/libavutil/ripemd.h
        ffmpeg/include/libavutil/samplefmt.h
        ffmpeg/include/libavutil/sha.h
        ffmpeg/include/libavutil/sha512.h
        ffmpeg/include/libavutil/spherical.h
        ffmpeg/include/libavutil/stereo3d.h
        ffmpeg/include/libavutil/tea.h
        ffmpeg/include/libavutil/threadmessage.h
        ffmpeg/include/libavutil/time.h
        ffmpeg/include/libavutil/timecode.h
        ffmpeg/include/libavutil/timestamp.h
        ffmpeg/include/libavutil/tree.h
        ffmpeg/include/libavutil/twofish.h
        ffmpeg/include/libavutil/tx.h
        ffmpeg/include/libavutil/version.h
        ffmpeg/include/libavutil/video_enc_params.h
        ffmpeg/include/libavutil/xtea.h
        ffmpeg/include/libpostproc/postprocess.h
        ffmpeg/include/libpostproc/version.h
        ffmpeg/include/libswresample/swresample.h
        ffmpeg/include/libswresample/version.h
        ffmpeg/include/libswscale/swscale.h
        ffmpeg/include/libswscale/version.h


        main.cpp)
#message(${PROJECT_SOURCE_DIR})

#target_link_libraries(${PROJECT_NAME} ffmpeg)
