# 游戏的Windows On ARM移植

这个游戏是N年前一个高手开源的，现在是找不到原作者了。利用了电子基盘的图片资源参考了很多当时街机麻将的游戏。

我开这个库是准备把他移植到Windows 8.1 RT/Windows 10 on ARM上， 好在我的Lumia上面玩：） 

Alpha version：
・SDL2  ARM移植完成
・代码从SDL移植到了SDL2，WOA上能基本运行，还需要进一步调试修改BUG

TODO：
・解决WAV音效无法播放问题
・WOA 听牌胡牌崩溃问题
・RT 上无法正常启动问题
