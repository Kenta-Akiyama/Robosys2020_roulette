# Robosys2020_roulette
ロボットシステム学の課題で作成したブログラム  

# 概要
講義内で作成したデバイスドライバを改造し、ルーレットを作成しました。  

# 動作環境
・Raspberry Pi 4 Model B  
・Ubuntu 20.04  

# 使用部品
・LED　×５  
・220Ω抵抗　×５  
・圧電スピーカー  
・ジャンパーワイヤー  
・ブレッドボード  

# 回路
![回路](https://imgur.com/a/yXEK7Du)
# 実行方法
インストール  
$ make  
$ cd Robosys_Devicedriver/myled  
$ sudo insmod myled.ko  
$ sudo chmod 666 /dev/myled0  

ルーレット開始  
echo 0 > /dev/mydev0  
LED消灯、止まるまでの値再設定
echo 1 > /dev/mydev0  


# 動画
・ Youtube  
[![](https://img.youtube.com/vi/Mp_nhySBATs/0.jpg)](https://www.youtube.com/watch?v=Mp_nhySBATs)  
# ライセンス
GNU General Public License v3.0  
