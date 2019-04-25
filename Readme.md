文本编辑器ver2.0
===
    一个具有使用意义的文本编辑器。

考虑的问题：
---
1.模块、接口的设计
###
2.可选择编码方式
###
3.CUI以及GUI
###
    ...
###

项目需求说明
===
一、功能需求
---
1.读写文件
###
    一个文本编辑器最基本的需求就是能对文件进行读取、保存。
2.多种编辑功能
###
    包括但不限于插入、删除、查找、复制、剪切、粘贴等。
3.编码可选
###
    可选择不同的编码进行保存或者打开文件。
4.可加载插件（*）
###
    可以加载利用某种语言编写的插件提供新的功能。

二、系统的划分
---
+------------------------------------+  
|界面层|负责显示以及提供操作提示             
|------------------------------------|  
|状态层|负责状态切换以及根据输入进行操作  
|------------------------------------|  
|功能层|负责提供操作功能调用  
|------------------------------------|  
|数据层|负责处理数据              
+------------------------------------+  

1.数据层接口
###
    （1）指向数据起始位置的指针  
    （2）指向光标位置的指针  
    （3）该数据块的必要信息  
    （4）指针的操作方法  
    （5）利用指针的数据处理方法  
    （6）不利用指针的数据处理方法  
2.功能层接口
###    
    （1）各种操作方法  
    （2）显示的缓存块  
3.状态层接口
###
    （1）状态切换方法  
    （2）操作逻辑  
