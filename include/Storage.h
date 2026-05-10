#ifndef STORAGE_H
#define STORAGE_H

template <class T>
class Storage
{
private:
    T data[100];
    int count;

public:
    Storage();
    bool add(const T &item);
    bool removeById(int id);
    T *findById(int id);
    const T *findById(int id) const;
    T *getAll();
    const T *getAll() const;
    int size() const;
    void clear();
};

template <class T>
Storage<T>::Storage()
{
    count = 0;
}

template <class T>
bool Storage<T>::add(const T &item)
{
    if (count >= 100)
    {
        return false;
    }

    data[count] = item;
    count++;
    return true;
}

template <class T>
bool Storage<T>::removeById(int id)
{
    int index = 0;
    while (index < count)
    {
        if (data[index].getId() == id)
        {
            int moveIndex = index;
            while (moveIndex < count - 1)
            {
                data[moveIndex] = data[moveIndex + 1];
                moveIndex++;
            }
            count--;
            return true;
        }
        index++;
    }
    return false;
}

template <class T>
T *Storage<T>::findById(int id)
{
    int index = 0;
    while (index < count)
    {
        if (data[index].getId() == id)
        {
            return &data[index];
        }
        index++;
    }
    return 0;
}

template <class T>
const T *Storage<T>::findById(int id) const
{
    int index = 0;
    while (index < count)
    {
        if (data[index].getId() == id)
        {
            return &data[index];
        }
        index++;
    }
    return 0;
}

template <class T>
T *Storage<T>::getAll()
{
    return data;
}

template <class T>
const T *Storage<T>::getAll() const
{
    return data;
}

template <class T>
int Storage<T>::size() const
{
    return count;
}

template <class T>
void Storage<T>::clear()
{
    count = 0;
}

#endif
