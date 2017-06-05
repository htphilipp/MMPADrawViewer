#ifndef KEYPRESSCATCHER_H
#define KEYPRESSCATCHER_H


class keyPressCatcher
{
public:
  keyPressCatcher():QObject();
  ~keyPressCatcher();

  bool eventFilter(QObject* object,QEvent* event);

};

#endif // KEYPRESSCATCHER_H
