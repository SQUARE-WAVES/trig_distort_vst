# trig_distort_vst

this is a lil tiny example VST3 plugin, mostly meant to show off how to get a vst plugin up and running without needing an external framework or something like that.

This is more meant to be something that you can copy and edit as a starting point rather than something you should change and modify yourself. As to liscenses and such this is basically provided as-is and I make no promises that it works or that it's good or that you should use it, in fact I reccomend you don't use it and instead just look at it for educational purposes. It exists to accompany [this post](https://serv.themysterioush.net/audio_lessons/how_to_vst3.html) where I walk through things as an explanation.

# how do I build it.

you are gonna need to get cmake, and the [vst3 sdk](https://github.com/steinbergmedia/vst3sdk)

then just go into the folder, make a build directory and do :
```
cmake -S <the project root> -B <your build directory> -DSDK_SOURCE_DIR=<path to your VST3 source> -DCMAKE_BUILD_TYPE=<Debug, or Release or something like that> -DSMTG_ADD_VSTGUI=OFF
``` 
then hop in the build directory and use make

I made the VST3 source directory an option because I don't wanna tell you where to put it, but if you use this as a jumping off point I'd reccomend changing that line in the CMakeLists to a set(Dvst3sdk_SOURCE_DIR "yr path here") so its less of a pain.

I've only tested this on my mac computer, but it should in theory work find not on a mac, as most of the cmake stuff is cross-platform.

# how do I learn more?
look at the post or read up on vst3. This is really meant to be a tiny little starting point.