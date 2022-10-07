#pragma once


namespace Protocol
{
	class KeyInput;
}

class Client;
//Ui가 있을때만 쓰니까 Broadcast해도 문제 없을 듯 
class UIState
{
public:
	virtual void Render(Client* GM);
	virtual void Update(Client* GM){}
	virtual void HandleInput(Client* GM) {}
	static string Loading(int& count);

protected:
	float center = 0.47;
	float bottomHRate = 0.15;
	float topHRate = 0.8;
};
class Init : public UIState
{
public:
	static Init* instance()
	{
		static Init* instance = new Init();
		return instance;
	}
	void Render(Client* GM) override;
	void HandleInput(Client* GM) override;

private:
	int _count = 0;
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
private:
	bool _matchingState = false;
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

	void Update(Client* GM) override;
	void Render(Client* GM) override;
	void HandleInput(Client* GM) override;
private:
	int _count = 0;

	bool _lState = false;
	bool _rState = false;

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