#pragma once

class Client;

class UIState
{
public:
	virtual void Render(Client* GM);
	virtual void HandleInput(Client* GM) {}
};

class Lobby : public UIState
{
public:
	static Lobby* instance()
	{
		static Lobby* instance = new Lobby();
		return instance;
	}

	void Render(Client* GM) override;

	void HandleInput(Client* GM) override;

};

class Matching : public UIState
{
public:
	static Matching* instance()
	{
		static Matching* instance = new Matching();
		return instance;
	}
	void Render(Client* GM) override;
	void HandleInput(Client* GM) override;

private:
	int _count = 0;
};
class GameReady : public UIState
{
public:
	static GameReady* instance()
	{
		static GameReady* instance = new GameReady();
		return instance;
	}
	void Render(Client* GM) override;
	void HandleInput(Client* GM) override;

private:
	int _count = 0;
};

class Playing : public UIState
{
public:
	static Playing* instance()
	{
		static Playing* instance = new Playing();
		return instance;
	}
	void Render(Client* GM) override;
	void HandleInput(Client* GM) override;
private:
	int _count = 0;
};

class Win : public UIState
{
public:
	static Win* instance()
	{
		static Win* instance = new Win();
		return instance;
	}
	void Render(Client* GM) override;
	void HandleInput(Client* GM) override;
};