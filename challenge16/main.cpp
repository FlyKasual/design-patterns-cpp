#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;

template <typename T>
struct IObserver {
	virtual void handleStateChange(T) = 0;
};

template <typename T>
struct IObserverSubject {
	virtual T getState() = 0;

	virtual void addObserver (IObserver<T>* o) {
		observers.push_back(o);
	};

	virtual void removeObserver(IObserver<T>* o) {
		observers.erase(
			remove(
				observers.begin(),
				observers.end(),
				o
			),
			observers.end()
		);
	};

	virtual void notifyObservers() {
		for (auto o : observers) {
			o->handleStateChange(getState());
		}
	};

protected:
	vector<IObserver<T>*> observers;
};

struct IRat : IObserver<int>
{
};

struct Game : IObserverSubject<int>
{
	void addRat(IRat* rat) {
		addObserver(rat);

		notifyObservers();
	}

	void removeRat(IRat* rat) {
		removeObserver(rat);

		notifyObservers();
	}

protected:
	int getState() {
		return observers.size();
	}
};

struct Rat: IRat
{
	Game& game;
	int attack{ 1 };

	Rat(Game& game): game(game) {
		game.addRat(this);
	}

	~Rat() {
		game.removeRat(this);
	}

	void handleStateChange(int newAttack) override {
		attack = newAttack;
	}
};

// namespace
// {

// 	class Evaluate: public ::testing::Test {};

// 	TEST_F(Evaluate, SingleRatTest) {
// 		Game game;
// 		Rat rat{ game };
// 		ASSERT_EQ(1, rat.attack);
// 	}

// 	TEST_F(Evaluate, TwoRatTest) {
// 		Game game;
// 		Rat rat{ game };
// 		Rat rat2{ game };
// 		ASSERT_EQ(2, rat.attack);
// 		ASSERT_EQ(2, rat2.attack);
// 	}

// 	TEST_F(Evaluate, ThreeRatsOneDies) {
// 		Game game;
// 		Rat rat{ game };
// 		ASSERT_EQ(1, rat.attack);

// 		Rat rat2{ game };
// 		ASSERT_EQ(2, rat.attack);
// 		ASSERT_EQ(2, rat2.attack);

// 		{
// 			Rat rat3{ game };

// 			ASSERT_EQ(3, rat.attack);
// 			ASSERT_EQ(3, rat2.attack);
// 			ASSERT_EQ(3, rat3.attack);
// 		}

// 		ASSERT_EQ(2, rat.attack);
// 		ASSERT_EQ(2, rat2.attack);
// 	}

// }  // namespace

int main(int ac, char* av[]) {

	Game game;
	Rat rat{ game };
	Rat rat2{ game };

	{
		Rat rat3{ game };
	}

	return EXIT_SUCCESS;
}
