# Qt资源文件无效问题
如果再Qt的库中有资源文件，并且和应用程序的资源文件同名，在linux下库的资源文件会找不到，windows下则没有问题。
解决方法：把库中的资源文件重新命名。

英文资料:
This problem usually happen when you have two Resource file with same name!(*.qrc).
For testing create a main project and create an external library project. Create two res.qrc file with same name.
Sometimes you can not see the icons and images on forms or dialogs on the library you have attached to your project. 
It is rare to see as usually a little number of programmers create a dialog in their LIBS. (for example having your own MESSAGEBOX in an external LIB)
I think this is a bug which should be reported to 'qt but report site'