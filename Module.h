#pragma once
class Module {
protected:
	bool m_running = true;
public:
	virtual void Update() = 0;

	inline bool IsRunning() const { return m_running; }

	static void Run(Module*module);
};
