#include <iostream>
#include <vector>
#include <map>
#include <cstdint>
#include <string>
#include <memory>
#include <initializer_list>


//this is paper oriented databese.
//if you need json like format.
//it needs some library.
//you dont think to like a databese + json=heaven.
//but it hell.

template<class K,class T>
class ObjectDataBaseII {
public:
	class Item;
	ObjectDataBaseII() {}
	ObjectDataBaseII(const std::initializer_list<std::pair<std::string,std::shared_ptr<Item>>>& In) :D(In.begin(), In.end()) {}
	class Item {
	public:

		Item(){}
		Item(const std::initializer_list<std::pair<K, std::vector<T>>>& In) :D(In.begin(), In.end()) {}

		typedef std::shared_ptr<Item> SharedItem;
		typedef std::vector<SharedItem> SharedItems;

		bool Add(const K& Tag, const T& In) {
			D[Tag].push_back(In);
			return true;
		}

		std::vector<T>& Find(const K& Tag) {
			auto It = D.find(Tag);
			if (It == D.end()) { return {}; }
			return It->second;
		}

		bool Change(const K& In, const std::vector<T>& V) {
			auto It = D.find(In);
			if (It != D.end()) {
				D[In].second = V;
			}

			return true;
		}
		bool Erase(const K& In) {
			D.erase(In);
			return true;
		}
		bool Clear() {
			D.clear();
			return true;
		}
		const std::vector<T>& Speak(const K& Tag) {
			auto It = D.find(Tag);
			return It->second;
		}
		std::size_t Size() {
			return D.size();
		}

		std::vector<T>& operator [](const K & X) {
			return D[X];
		}
		typename std::map<K, std::vector<T>>::iterator begin() {
			return D.begin();
		}
		typename std::map<K, std::vector<T>>::iterator end() {
			return D.end();
		}

		std::map<K, std::vector<T>>& Get() {
			return D;
		}
	protected:
		std::map<K, std::vector<T>> D;
	};

	bool Add(const std::string& Tag, typename Item::SharedItem In) {
		D[Tag] = In;
		return true;
	}
	typename Item::SharedItems Find(const K& In) {

		typename Item::SharedItems R;

		for (auto& o : D) {
			for (auto& oo:(*(o.second))) {
				if (oo.first == In) {
					R.push_back(o.second);
				}
			}
		}
		return R;
	}
	bool Clear() {
		D.clear();
		return true;
	}
	bool Erase(const std::string& Tag) {
		D.erase(Tag);
		return true;
	}

protected:
	std::map<std::string, typename Item::SharedItem> D;
};

typedef ObjectDataBaseII<std::string, std::string> ODB;

int main() {
	auto A = std::make_shared < ODB::Item > ();
	auto B = std::make_shared < ODB::Item > ();
	auto C = std::make_shared < ODB::Item >();
	A->Add("A", "Hoge");
	A->Add("B", "kkekkke");

	(*A)["A"].push_back("gogogo");

	ODB X;

	X.Add("Hoge", A);
	X.Add("are", B);

	auto Y = X.Find("A");

	A->Speak("A").size();

	return 0;
}