# Design of Rook Program

Design principles are as follows:

1. Prefer stack to heap. Less worry about trying to track down potential memory leaks, etc.

**Example**

```cpp
// preferred
class MyWidget : public QWidget
{
   QLabel myLabel;
   QPushButton myButton;
};

// not preferred
class MyWidget2 : public QWidget
{
   QLabel *myLabel; // new
   QPushButton *myButton; // new
};
```

2. Dialogs should be parent-less. This way dialogs have their own window, etc.

**Example**

```cpp
MainWindow mainWindow;
mainWindow.show();

// later in program
void MainWindow::onMainWindowNew()
{
   NewDialog newDlg; // no parent
   newDlg.exec();
}
```