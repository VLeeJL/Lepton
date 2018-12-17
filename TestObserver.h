//
// Created by user on 18-12-17.
//

#ifndef LEPTON_TESTOBSERVER_H
#define LEPTON_TESTOBSERVER_H
#include "base/ObserverList.h"

   class MyObserverList {
    public:

     class Observer {
      public:
       virtual void OnFoo(MyObserverList* w) = 0;
       virtual void OnBar(MyObserverList* w, int x, int y) = 0;
     };

     void AddObserver(Observer* obs) {
       observer_list_.addObserver(obs);
     }

     void RemoveObserver(Observer* obs) {
       observer_list_.removeObserver(obs);
     }

     void NotifyFoo() {
       FOR_EACH_OBSERVER(Observer, observer_list_, OnFoo(this));
     }

     void NotifyBar(int x, int y) {
       FOR_EACH_OBSERVER(Observer, observer_list_, OnBar(this, x, y));
     }

    private:
     base::ObserverList<Observer> observer_list_;
   };

#endif //LEPTON_TESTOBSERVER_H
