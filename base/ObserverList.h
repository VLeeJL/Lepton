//
// Created by user on 18-12-17.
//

#ifndef LEPTON_OBSERVERLIST_H
#define LEPTON_OBSERVERLIST_H
#include "Base.h"
#include <memory>
#include <vector>
#include <limits>
namespace base
{
    template <typename ObserverType>
    class ObserverListBase
    {
    public:
        enum class NotificationType {NOTIFY_ALL, NOTIFL_EXISTING_ONLY};

        class Iterator
        {
        public:
            explicit Iterator(ObserverListBase<ObserverType>* list);
            ~Iterator();
            ObserverType* getNext();
        private:
            std::weak_ptr<ObserverListBase<ObserverType>> list_;
            size_t index_;
            size_t max_index_;
        };

        ObserverListBase() : notify_depth_(0), type_(NotificationType::NOTIFY_ALL) {}
        explicit ObserverListBase(NotificationType type) :
            notify_depth_(0), type_(type) {}
        NOCOPYABLE(ObserverListBase);

        void addObserver(ObserverType* obs);
        void removeObserver(ObserverType* obs);
        bool hasObserver(const ObserverType* obs) const;
        void clear();

    protected:
        size_t size() const { return observers_.size(); }
        void compact();

    private:
        using ListType = std::vector<ObserverType*>;
        ListType observers_;
        int notify_depth_;
        NotificationType type_;
        friend class ObserverListBase::Iterator;
    };

    template <typename ObserverType, bool check_empty = false>
    class ObserverList : public ObserverListBase<ObserverType>
    {
    public:
        using NotificationType = typename ObserverListBase<ObserverType>::NotificationType;
        ObserverList() = default;
        explicit ObserverList(NotificationType type) : ObserverListBase<ObserverType>(type) {}
        ~ObserverList();
        bool might_have_observer() const;
    };


#define FOR_EACH_OBSERVER(ObserverType, observer_list, func)                    \
    do {                                                                        \
        if (observer_list.might_have_observer())                                \
        {                                                                       \
            base::ObserverListBase<ObserverType>::Iterator iter(&observer_list);      \
            ObserverType* obs;                                                  \
            while ((obs = iter.getNext()) != nullptr)                          \
                obs->func;                                                      \
        }                                                                       \
    }                                                                           \
    while(0)                                                                    \

}
#endif //LEPTON_OBSERVERLIST_H
