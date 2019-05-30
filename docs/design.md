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

3. Game widgets and dialogs should be derived from scalable widgets and have scalable children. Scalable widgets are derived from QWidget classes.

**Example**

```cpp
// common.h
class ScalableQLabel : public QLabel
{
	ScalableQLabel(QWidget *parent = nullptr);
	void rescale();
	
	// override functions related to size or position
	void move(const QPoint &pos);
	void resize(const QSize &size);
};

class ScalableQDialog : public QDialog
{
	ScalableQDialog(QWidget *parent = nullptr);
	void rescale();
	
	// override functions related to size or position
	void move(const QPoint &pos);
	void resize(const QSize &size);
};

// gameInfoWidget.h
class GameInfoWidget : public ScalableQDialog
{
	// scalable children
	ScalableQLabel trumpLabel;
	ScalableQLabel pointsLabel;

	GameInfoWidget(QWidget *parent = nullptr);
	void rescale();
};
```

All game widgets and dialogs will automatically be resized according to ``scalefactor`` global. The ``scalefactor`` global can be customized by user (i.e. when they change the game resolution).

The ``rescale`` method is called for widgets shown on screen when ``scalefactor`` is changed. When the widget is created, ``scalefactor`` will be applied in each of the ``Scalable`` classes.

This approach to scaling is not complicated for programmer. All programmer needs to worry about is 

* deriving their widget from a scalable widget class
* deriving their children widgets from a scalable widget class
* defining a rescale method which calls the rescale method of all of the children classes.

If the programmer doesn't need a widget to be scalable, they don't need to do any of things mentioned above.

The scaling itself is handled by the ``Scalable`` classes.

4. 
