# Todo_manager

win下实现类似Taskwarrior的小东西
数据存放于D:/.todo

## 使用方法

- 显示帮助 `todo help`
- 添加任务 `todo add task0 1919:11:45-13:04:00 "这里输入备注"`
- 查看任务 `todo` 或者 `todo list`
- 查看任务备注 `todo detail 0`
- 移除任务 `todo remove 0`
- 更新任务 `todo update [name|deadline|detail] "值"`


## 设计文档

.todo中一行一个任务，task名字和备注部分用base64吧，支持空格换行啥的。

时间表示格式：
- 