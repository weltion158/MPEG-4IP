src

目录：
codec：包含有播放的CODEC，视频CODEC有MPEG4和WAV两种格式
                          音频CODEC有MP3和AA两种格式
osx：  包含了SDL连接库和播放器的控制参数
win_client： 包含了MPEG-4播放器的网络客户端应用
win_common： 网络客户端的播放器设置
win_gui：  播放器的图形化界面

player60.dsw  是一个总的VC工作区，它包括了命令行形式的播放器和图形化界面的播放器。
              打开后，利用Batch Build进行编译。
libmpplayer60.dsw： 播放器库文件的VC工作区，它包含在player60.dsw中了
mp4player60.dsw：   MPEG-4播放器的VC工作区，它编译生成的是命令行形式的播放器
wmp4player60.dsw：  MPEG-4播放器的VC工作区，它编译生成的是图形界面形式的播放器