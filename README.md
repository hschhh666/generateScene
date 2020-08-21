# 程序名
generateScene

# 输入 
卫星地图png


# 输出
yml和jpg文件，表示场景结构，标明了场景中的障碍物、出生/消失点和中间点。yml用于后续仿真器输入，jpg是给人看的，仅仅用来可视化。

# 使用方法
1. 在程序里设定好卫星地图的路径，以及输出路径（这里很蠢，没有写成参数形式，不过能用就行，嘻嘻）
1. 运行程序，
    * `o` 表示当前为绘制障碍物模式，在此模式下，按住拖动鼠标左键即可绘制矩形障碍物
    * `p` 表示当前为绘制出生/消失点模式，在此模式下点鼠标左键即可绘制出生消失点，为红色
    * `h` 表示当前为绘制中间点模式，在此模式下点鼠标左键即可绘制中间点，为绿色。
    * `q` 保存并退出
1. 为什么需要绘制中间点呢? 比如从1号门走向2号门，它们中间可能有墙，如果直接走的话行人会沿着墙走，很丑，也不符合实际，所以可以在它们中间添加中间点，先让行人走向该中间点，然后再走向2号门。那怎么能知道行人从2走到3时应该经过哪个中间点呢？这一部分没有通过程序实现，而是在程序运行结束生成yml后，由人手动看着地图改的。里面有个`HiddenMatrix`矩阵，其第`i`行`j`列表明从`i`号门走到`j`号门时需要经过第`(i,j)`个中间点，如果`(i,j)`为-1则不经过任何中间点。生成的yml文件中`HiddenMatrix`全是-1，需要手动改这个矩阵。
