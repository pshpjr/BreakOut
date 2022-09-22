#pragma once

class GameManager;

class UIState
{
public:
	virtual void Render(GameManager* GM);
	virtual void HandleInput(GameManager* GM) {}
};

class Lobby : public UIState
{
public:
	static Lobby* instance()
	{
		static Lobby* instance = new Lobby();
		return instance;
	}

	void Render(GameManager* GM) override;

	void HandleInput(GameManager* GM) override;

};

class Matching : public UIState
{
public:
	static Matching* instance()
	{
		static Matching* instance = new Matching();
		return instance;
	}
	void Render(GameManager* GM) override;
	void HandleInput(GameManager* GM) override;

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
	void Render(GameManager* GM) override;
	void HandleInput(GameManager* GM) override;

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
	void Render(GameManager* GM) override;
	void HandleInput(GameManager* GM) override;
};

class Win : public UIState
{
public:
	static Win* instance()
	{
		static Win* instance = new Win();
		return instance;
	}
	void Render(GameManager* GM) override;
	void HandleInput(GameManager* GM) override;
};