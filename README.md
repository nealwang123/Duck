<div align=center>
<img src="https://gitee.com/uploads/images/2018/0226/204052_d18504c9_20764.png" width="100" height="100" />
</div>


 Duck 基于Qt的插件式开发框架，他是一个简易的插件框架，所有业务由插件处理，与主框架无关，也可以把他称为程序的集合。由于要使用此框架开发个人项目，所以贡献出来让大家参考学习。
 

### Duck




 **运行环境** 

- windows
- Qt 5.9/5.12
- python2.7 OR python3



 **构建主框架** 

- 使用Qt Creator 打开Duck.pro  构建->运行
- 将AutoGetDllforWin.bat 放置主框架根目录下，他将程序所用的DLL拷贝至程序根目录，第三方库需要自己拷贝



 **新建插件** 

- 使用NewProject.py 会自动生成一个插件模板，你可以添加或者删除相应的Ui或者程序逻辑

- :fa-windows: + R

```
CMD

python NewProject.py

Enter Project Name: "输入插件名称按后回车键"
```

- 在plugin文件夹找到相应的插件文件夹，使用Qt Creator 打开相应的.pro文件 构建项目




 **运行** 

- 由于个人项目需要，目前插件为自动加载
- 将编译好的插件放置程序根目录，插件将自动加载



 **调试** 

- 目前尚未解决与主框架联调，其实也并不需要，因为主框架本没有什么可用的:stuck_out_tongue_winking_eye: 
- 分享我的调试方法，将插件写成可执行程序，然后将其变为插件。虽然方法Low了点，但是既简单又好用 :sunglasses: 





 **插件通信** 

- Shared Memory， Socket， Qt Remote Objects

********************************************************************************************************
**作者补充**

***本工程基于gitee开源作者小而强大的Duck项目完善，为尊重原创，工程名及相关说明保留。***
-  在参考工程和大神们的教程的学习过程中添加了必要注释；例如：Duck.pro、plugininterface.h等；
-  项目修改为子工程管理方式，方便统一管理;
-  临时文件指定目录；
-  添加了预编译头 head.h;
-  基于信号槽实现插件通信预留接口（当前注释,正在查找其它更好的方式实现）;
-  两个测试插件完全保留，仅修改工程管理文件（pro）；

**声明**
原作地址 https://gitee.com/penghongbin/QFrameWork
原作者虽开源了项目，但未指定开源许可证,如原作有要求我会及时调整项目





