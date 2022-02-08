# Todo_manager

win下实现类似Taskwarrior的小东西（完全比不上）
数据存放于D:/.todo

## 使用方法

将 exe 目录加入系统环境变量。在 cmd 或 powershell 等终端中输入命令使用。

- 显示帮助 `todo help`
- 添加任务 `todo add <任务名字> <任务ddl> <这里输入备注（可选）>`
- 查看任务 `todo` 
- 查看任务及细节 `todo list`
- 查看某个任务 `todo detail <任务编号>`
- 移除某个任务 `todo remove <任务编号>`
- 更新某个任务 `todo update [name|deadline|detail] <值>`
- 移除所有任务 `todo clear iamsuretoclearalltasks`

目前支持的 ddl 时间表示格式（不含合法性检查）：

- **现在** now **（会被记为 -1 ，表示越快越好）**
- **月日** mm-dd
- **年月日** yyyy-mm-dd
- **x 月后**xm
- **x 周后**xw
- **x 天后**xd

## 设计文档

.todo中一行一个任务，task名字和备注部分用base64，支持一下空格换行啥的。
