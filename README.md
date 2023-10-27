完成した処理

プレイヤー
モデルとモーション
移動やジャンプの基本挙動
ジャンプは飛ぶのではなく岩を足元に発生させて意図的に飛ばされるような表現とした。
二段ジャンプ，またはEnterキーで攻撃で壁を生成する。

ステージギミック
ブロック：特に特別な使用はない、テクスチャを貼ればステージの雰囲気とかをいじれる
すり抜け床：上の判定のみある細いブロック、下入力で当たり判定が無くなる
壁床とげ：上下左右に対応、とげの方向に触れるとプレイヤーのヒット処理へ入る
移動とげ：触れるとプレイヤーのヒット処理へ、上下の動きか左右の動きをする
大砲：一定間隔で弾を発射する。この弾は壁生成で防ぐことができる
ドア：スイッチと連動している場合はスイッチ起動中に開く、連動していなければドアに触れると開く
スイッチ：プレイヤーが生成した壁で起動できる。一定時間でオフになる

ボス戦の実装
ボスのイメージは今までのステージのギミックの複合体
攻撃パターンは４つ
大きいジャンプ
小さいジャンプ
変形して射撃
垂直ジャンプ後に床からとげ生成

ボスは３かい落とすと倒せる
１回落とすごとに無敵状態となって近づいてくる
加えて復活時にとげのギミックを配置するなど行っている

システム
エディットモードの実装、ステージギミックのオブジェクトを全て配置出来る。向きや連動したドアの配置なども実装し、ロードする位置を選べるのでステージ同士をくっつけて全体のマップを制作する。

GitのURL
https://github.com/sakamoto0316/Action00.git
