# Todo_manager
win下实现类似Taskwarrior的小东西
task的数据存放于C://.task

## 使用方法

- 显示帮助 `task help`
- 添加任务 `task add task0 1919:11:45-13:04:00 "这里输入备注"`
- 查看任务 `task` 或者 `task list`
- 查看任务备注 `task detail 0`
- 移除任务 `task remove 0`


## 设计文档

.task中一行一个任务，task名字和备注部分用base64吧，支持空格换行啥的。