#pragma once
#include <type_traits>
#include <iostream>
#include <queue>
#include <vector>
class MessageManager
{
public:
	
	template<typename Message> static void PushMessage(Message message)
	{
		messageVector<Message>->push_back(message);
	}

	template<typename Message> static Message* PopMessage(unsigned int offsetIndex)
	{
		if (HasNext<Message>(offsetIndex))
		{
			unsigned int offset = offsetVector<Message>->at(offsetIndex);
			IncrementOffsetAtIndex<Message>(offsetIndex);
			return &(messageVector<Message>->at(offset));
		}
		return nullptr;
	}

	template<typename Message> static void ClearMessages()
	{
		messageVector<Message>->clear();
		offsetVector<Message>->clear();
	}

	template<typename Message> static bool HasNext(unsigned int offsetIndex)
	{
		unsigned int offset = offsetVector<Message>->at(offsetIndex);
		if (offset < messageVector<Message>->size())
		{
			return true;
		}
		return false;
	}

	template<typename Message> static unsigned int GetNewOffsetIndex()
	{
		return AddNewOffset<Message>();
	}
	
private:
	MessageManager() {};
	~MessageManager() {};

	template<typename Message> static unsigned int AddNewOffset()
	{
		unsigned int newIndex = offsetVector<Message>->size();
		offsetVector<Message>->push_back(0);
		return newIndex;
	}

	template<typename Message> static void IncrementOffsetAtIndex(unsigned int index)
	{
		SetOffsetAtIndex<Message>(index, offsetVector<Message>->at(index) + 1);
	}

	template<typename Message> static void SetOffsetAtIndex(unsigned int index, unsigned int offset)
	{
		offsetVector<Message>->at(index) = offset;
	}

	template<typename T> static inline std::vector<T>* messageVector = new std::vector<T>;
	template<typename T> static inline std::vector<unsigned int>* offsetVector = new std::vector<unsigned int>;
};