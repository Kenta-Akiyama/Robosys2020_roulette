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

# 実行方法
インストール  
$ make  
$ cd Robosys_Devicedriver/myled  
$ sudo insmod myled.ko  
$ sudo chmod 666 /dev/myled0  

# 動画
・ Youtube  
<https://youtu.be/Mp_nhySBATs>  
# ライセンス
