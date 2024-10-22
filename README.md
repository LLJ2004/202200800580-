这是一个简单的C语言餐厅管理系统
餐饮系统使用技巧：
exe可运行程序位置：C语言点餐系统\点餐系统程序\x64\Release\Restaurant1.exe
点开程序，进入用户身份选择界面

先按1，进入管理员模式：
初始时，工号和密码均为admin（登录后可修改）
登录后：
按1：查看餐厅当前的座位信息，方括号中为空表示该座位无人，方括号中为*表示该座位有人，并且可查看当前餐厅有多少位顾客，查看结束，请按enter返回上一级菜单
按2：查看餐厅的营业总额
按3：更改菜品，输入“ add [菜品名] [价格] ” 即可完成添加菜品的功能；输入“ del [菜品序号] ”可以实现删除菜品的功能；输入“ quit ”可以返回上一级菜单；
按4：更改服务员（员工）输入“ add [工号] [姓名] " 添加员工，初始化密码为123456；输入" del [工号] " 删除员工；输入" quit " 返回上一级菜单；
按5：更改 VIP，输 入 " add [卡 号] [电 话] " 添 加 VIP顾 客； 输 入 "del [卡 号]" 删 除 VIP；输 入 "quit" 返 回 上 一 级 菜 单
按6：更改密码，旧密码是admin，新密码自定；
按7：菜品分析。展示当前菜品信息及销量
按8：退出管理员模式
按0：退出命令框，程序over


如果您是在选择管理员和服务员的窗口，按2进入服务员模式：
系统预置了三位服务员
工号	姓名	初始密码
100001	long	123456
100002	zhu 	123456
100003	chang 	123456
可以任选一位员工登录，或在管理员系统添加员工登录

按1：进行座位预定：方括号中为空表示该座位无人，方括号中为@表示正在用餐的顾客，方括号中为*表示该座位有人，输入餐桌号即可进行预定，如果座位已有人选，屏幕会给予提醒，重新选择即可；该餐桌地图为横9竖7的地图，座位会转化为某行某列；按0返回上一级菜单；
按2：可以展示菜品，按0退出返回上一级菜单；
按3：进行订餐。需预约座位后方可进行点餐。点餐时，先输入顾客桌号，再输入餐品的序号就可以点餐，输入0退出订餐返回上一级菜单；
按4：结账服务，按照屏幕要求先输入桌号（是哪一桌要缴费）。接着系统会询问顾客是否是VIP。如果顾客是VIP，需要输入y并且输入VIP手机号，系统判断是VIP的顾客会进行打折服务；如果顾客不是VIP，输入n即可，该顾客订单不会进行打折。最后输入所需缴费的金额即可。退出按enter键，返回上一级菜单；如果没有顾客缴费，按0返回上一级菜单；
按5：取消预订，输入想要取消预定的桌号即可，如果没有输入0返回上一级菜单；
按6：修改服务员密码，旧密码是123456，新密码自定；
按7：退出服务员模式
按0：退出命令框，程序over：

