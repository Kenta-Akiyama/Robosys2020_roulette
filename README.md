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
![回路](https://i.gyazo.com/216184697331e5377520e8413845adf5.png)  
画像ではRaspberry Pi ３を使用していますが、実際にはRaspberry Pi 4を使用しています。  

LEDはGPIO 21,20,16,12,26 の順で光ります。  
スピーカーは必ず１９につないでください。  
# 実行方法

インストール  
```
$ git clone https://github.com/Kenta-Akiyama/Robosys2020_roulette.git  
$ cd Robosys2020_roulette  
$ make  
$ sudo insmod mydev.ko  
$ sudo chmod 666 /dev/mydev0  
```

ルーレット開始  
```
echo 0 > /dev/mydev0  
```

LED消灯、ルーレットが止まるまでの値再設定  
```
echo 1 > /dev/mydev0  
```

# 動画
・ Youtube  
[![](https://img.youtube.com/vi/Mp_nhySBATs/0.jpg)](https://www.youtube.com/watch?v=Mp_nhySBATs)  
# ライセンス
GNU General Public License v3.0  
