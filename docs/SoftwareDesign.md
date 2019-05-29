1. Prefer stack to heap. 

**Preferred**

```cpp
class MyWidget : public QWidget
{
   QLabel myLabel;
   QPushButton myButton;
};
```

**Not Preferred**

```cpp
class MyWidget : public QWidget
{
   QLabel *myLabel; // new
   QPushButton *myButton; // new
};
