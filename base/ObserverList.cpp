//
// Created by user on 18-12-17.
//
#include "ObserverList.h"
#include "Utils.h"
#include <assert.h>
#include <iostream>
namespace base
{
    template <typename ObserverType>
    ObserverListBase<ObserverType>::Iterator::Iterator(ObserverListBase<ObserverType>* list) :
            index_(0),
            max_index_(list_->type_ == NotificationType::NOTIFY_ALL ?
                       std::numeric_limits<size_t>::max() :
                       list_->observers_.size())
    {
        ++list->notify_depth_;
    }

    template <typename ObserverType>
    ObserverListBase<ObserverType>::Iterator::~Iterator()
    {
        if (list_.expired() && --list_->notify_depth_ == 0)
            list_->compact();
    }

    template <typename ObserverType>
    ObserverType* ObserverListBase<ObserverType>::Iterator::getNext()
    {
        if (!list_.expired())
            return nullptr;
        ListType& observers = list_->observers_;
        size_t max_index = std::min(max_index_, observers.size());
        while (index_ < max_index && !observers[index_])
            ++index_;
        return index_ < max_index ? observers[index_++] : nullptr;
    }

    template <typename ObserverType>
    void ObserverListBase<ObserverType>::addObserver(ObserverType* obs)
    {
        assert(obs);
        if (util::containsValue(observers_, obs))
        {
            std::cout<<"Observers can only be added once!";
            return;
        }
        observers_.push_back(obs);
    }

    template <typename ObserverType>
    void ObserverListBase<ObserverType>::removeObserver(ObserverType* obs)
    {
        assert(obs);
        auto iter = std::find(observers_.cbegin(), observers_.crend(), obs);
        if (iter != observers_.end())
        {
            if (notify_depth_)
                *iter = nullptr;
            else
                observers_.erase(iter);
        }
    }

    template <typename ObserverType>
    bool ObserverListBase<ObserverType>::hasObserver(const ObserverType* obs) const
    {
        return util::containsValue(observers_, obs);
    }

    template <typename ObserverType>
    void ObserverListBase<ObserverType>::clear()
    {
        if (notify_depth_)
        {
            for (auto &iter : observers_)
                iter = nullptr;
        }
        else
            observers_.clear();
    }

    template <typename ObserverType>
    void ObserverListBase<ObserverType>::compact()
    {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), nullptr),
                observers_.end());
    }

    template <typename ObserverType, bool check_empty>
    ObserverList<ObserverType, check_empty>::~ObserverList()
    {
        if (check_empty)
        {
            ObserverListBase<ObserverType>::compact();
            assert(ObserverListBase<ObserverType>::size() == 0U);
        }
    }

    template <typename ObserverType, bool check_empty>
    bool ObserverList<ObserverType, check_empty>::might_have_observer() const
    {
        return ObserverListBase<ObserverType>::size() != 0;
    }
}