#pragma once

#include "Includes.h"

class AlphaSkipper
{
public:
    AlphaSkipper()
        : counter(0)
    {

    }

    AlphaSkipper(const AlphaSkipper&)
        : counter(0)
    {

    }

    bool operator()()
    {
        return counter++ % 4 < 3;
    }

    bool operator()(int)
    {
        return counter++ % 4 < 3;
    }

private:
    int counter;
};

class NSkipper
{
public:
    NSkipper()
        : counter(0), fullSize(4), dataSize(3)
    {

    }

    NSkipper(const NSkipper& nSkipper)
        : counter(0), fullSize(nSkipper.fullSize), dataSize(nSkipper.dataSize)
    {

    }

    NSkipper(const int _fullSize, const int _paddingSize)
        : counter(0), fullSize(_fullSize), dataSize(_fullSize - _paddingSize)
    {

    }

    bool operator()()
    {
        return counter++ % fullSize < dataSize;
    }

    bool operator()(int)
    {
        return counter++ % fullSize < dataSize;
    }

private:
    int counter;
    int fullSize;
    int dataSize;
};

class ChannelDuplicator
{
public:
    ChannelDuplicator()
        : counter(0), channelNumber(3)
    {

    }

    ChannelDuplicator(const ChannelDuplicator& channelDuplicator)
        : counter(0), channelNumber(channelDuplicator.channelNumber)
    {

    }

    ChannelDuplicator(const int _channelNumber)
        : counter(0), channelNumber(_channelNumber)
    {

    }

    bool operator()()
    {
        return counter++ % channelNumber == (channelNumber - 1);
    }

    bool operator()(int)
    {
        return counter++ % channelNumber == (channelNumber - 1);
    }

private:
    int counter;
    const int channelNumber;
};

template<typename Container, typename Predicate>
class variable_back_insert_iterator
{
public:
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
    using pointer = void;
    using reference = void;

    using container_type = Container;
    using container_value_type = typename Container::value_type;

#ifdef __cpp_lib_concepts
    using difference_type = ptrdiff_t;

    constexpr variable_back_insert_iterator() noexcept = default;
#else
    using difference_type = void;
#endif

    constexpr explicit variable_back_insert_iterator(Container& _container, Predicate _predicate,
        container_value_type _alternativeValue) noexcept
        : container(std::addressof(_container)), predicate(_predicate), alternativeValue(_alternativeValue)
    {

    }

    constexpr variable_back_insert_iterator& operator=(const container_value_type& value) noexcept
    {
        if (predicate())
            container->push_back(std::move(value));
        else
            container->push_back(alternativeValue);

        return *this;
    }

    constexpr variable_back_insert_iterator& operator=(container_value_type&& value) noexcept
    {
        if (predicate())
            container->push_back(std::move(value));
        else
            container->push_back(alternativeValue);

        return *this;
    }

    constexpr variable_back_insert_iterator& operator*() noexcept
    {
        return *this;
    }

    constexpr variable_back_insert_iterator& operator++() noexcept
    {
        return *this;
    }

    constexpr variable_back_insert_iterator operator++(int) noexcept
    {
        return *this;
    }

private:
    Container* container;
    Predicate predicate;
    container_value_type alternativeValue;
};

template<typename Container, typename Predicate>
constexpr variable_back_insert_iterator<Container, Predicate> variable_back_inserter(Container& container, Predicate predicate,
    typename Container::value_type alternativeValue) noexcept
{
    return variable_back_insert_iterator<Container, Predicate>(container, predicate, alternativeValue);
}

template<typename Container, typename Predicate>
struct conditional_iterator
{
    using iterator_category = std::forward_iterator_tag;
    using value_type = typename Container::value_type;
    using difference_type = typename Container::difference_type;
    using pointer = typename Container::pointer;
    using reference = value_type&;

    using iterator_type = typename Container::iterator;

    conditional_iterator() = default;

    conditional_iterator(iterator_type _iterator, Predicate _predicate)
        : iterator(_iterator), predicate(_predicate)
    {

    }

    conditional_iterator& operator++()
    {
        if (predicate())
        {
            iterator++;
        }

        return *this;
    }

    conditional_iterator operator++(int junk)
    {
        conditional_iterator it = *this;

        if (predicate())
        {
            iterator++;
        }

        return it;
    }

    reference operator*() const
    {
        return *iterator;
    }

    pointer operator->() const
    {
        return &(operator*());
    }

    bool operator==(const conditional_iterator& _iterator) const
    {
        return iterator == _iterator.iterator;
    }

    bool operator!=(const conditional_iterator& _iterator) const
    {
        return iterator != _iterator.iterator;
    };

private:
    iterator_type iterator;
    Predicate predicate;
};

template<typename Iterator, typename Container>
constexpr void ConvertRGBBufferToRGBA(Iterator rgbBufferBeginIterator, Iterator rgbBufferEndIterator, Container& rgbaBuffer)
{
    auto beginIterator = conditional_iterator<Container, AlphaSkipper>(rgbBufferBeginIterator, AlphaSkipper());
    auto endIterator = conditional_iterator<Container, AlphaSkipper>(rgbBufferEndIterator, AlphaSkipper());

    std::copy(beginIterator, endIterator, variable_back_inserter(rgbaBuffer, AlphaSkipper(), 0));

    rgbaBuffer.push_back(0);
}

template<typename Iterator, typename Container>
constexpr void ConvertRGBABufferToRGB(Iterator rgbaBufferBeginIterator, Iterator rgbaBufferEndIterator, Container& rgbBuffer)
{
    std::copy_if(rgbaBufferBeginIterator, rgbaBufferEndIterator, std::back_inserter(rgbBuffer), AlphaSkipper());
}

template<typename Iterator, typename Container>
constexpr void ConvertRBufferToRGB(Iterator rBufferBeginIterator, Iterator rBufferEndIterator, Container& rgbBuffer)
{
    auto beginIterator = conditional_iterator<Container, ChannelDuplicator>(rBufferBeginIterator, ChannelDuplicator());
    auto endIterator = conditional_iterator<Container, ChannelDuplicator>(rBufferEndIterator, ChannelDuplicator());

    std::copy(beginIterator, endIterator, std::back_inserter(rgbBuffer));
}
