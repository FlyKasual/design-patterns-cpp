#include <vector>
struct IParticipant
{
	virtual void notify(IParticipant*, int) = 0;
};

struct Mediator
{
	std::vector<IParticipant*> participants;

	Mediator() = default;

	void broadcast(IParticipant* source, int value) {
		for (auto p : participants)
			p->notify(source, value);
	}
};

struct Participant: IParticipant
{
	int value{ 0 };
	Mediator& mediator;

	Participant(Mediator& mediator): mediator(mediator) {
		mediator.participants.push_back(this);
	}

	void say(int value) {
		mediator.broadcast(this, value);
	}

	virtual void notify(IParticipant* source, int value) override {
		if (source != this)
			this->value += value;
	}
};
