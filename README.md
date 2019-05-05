# Interval Tree based on RB tree

区间树（继承于红黑树）
支持操作：
（定义于main.c中）

void Insert(numtype num, int low, int high, string name);
> 插入一门课程，num:课程编号,[low, high] 课程区间， name:课程名称

void Show();
> 中序遍历打印课程

void Search_All(int low, int high);
> 搜索指定区间内的所有课程并打印

void SeqTraverse()
> 层序遍历

void Delect_One(int low, int high);
> 删除指定区间的课程

void Delect_All(int low, int high);
> 删除指定区间的所有课程

