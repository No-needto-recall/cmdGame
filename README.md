# cmdGame

# 仓库简介

基于C++开发的宝可梦游戏
开发环境目前基于windows
配置文件采用 nlohmann/json库

本仓库将采用GitHub Flow的流程

1. 时常保持master分支可以部署的状态
2. 进行新的作业时要从master分支创建新分支，新分支名称要具有描述性
3. 在2新建的本地仓库分支中进行提交
4. 在GitHub端仓库创建同名分支，定期push
5. 需要帮助或反馈时创建Pull Request,以Pull Request进行交流
6. 让其他开发者进行审查，确认作业完成后与master分支合并
7. 与master分支合并后立即部署


+ ！没有进行过测试或者测试未通过的代码绝不可以合并到master分支
+ ！进行新的作业时要从master分支创建新分支，无论是添加新功能还是修复BUG都是如此
+ ！新分支的名称要具有描述性
+ ！提交Pull Request的人需要去审核上一个提交的Pull Request,对其负责


# 仓库目录

+ bin:可执行程序
+ conf:配置文件
+ include:头文件
+ lib:库
+ log:日志文件
+ src:源文件
+ test:visual studio2022的测试目录

# 说明

test目录下有工程设置test.sln
用visual studio 2022打开可以项目

如果出现v144工具集等级不够的情况，请手动更改：
1. 打开解决方案资源管理器
2. 选中test项目，右键属性
3. 打开配置属性中，常规
4. 平台工具集选中你目前的工具集
5. 重定向项目
