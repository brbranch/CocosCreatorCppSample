# CocosCreatorCppSample
CocosCreator v1.4 + cocos2d-x v3.14で作成したサンプルです。ついでにCocosCreatorの勉強も兼ねて1dayチャレンジしてみました。

# Cocos Creatorをcocos2d-x(c++版)で使う方法
see http://brbranch.jp/blog/201704/cocos2d-x/cocoscreator_cpp/

# 素材について
作成にあたって色々と素材を使わせてもらってたのですが、なんとなく利用規約に反しそうな気がしたので
使ってた素材はレポジトリから削除してます。
(いちおうはビルドしたら動くようにはなってると思う)

# ビルド方法
## iOSのビルド
Xcodeから ``proj.ios_mac``にある``CocosCreatorCppSample.xcodeproj`` を立ち上げてテキトーにビルドしてみてください。

## Androidのビルド
cocosコマンドがあることが前提です。
レポジトリ直下から以下のコマンドをうちます。

```
cocos compile -p android --android-studio
```

# ライセンス
基本Mitライセンスですが、ソースについては、以下を除いた全て[NYSLライセンス](http://www.kmonos.net/nysl/)になります。   
(以下はMitライセンスになると思うけどまあ正直あんまりよくわかんない)
* Classes/AppDelegate.h
* Classes/AppDelagete.cpp
* Classes/reader直下の全ファイル
