#ifndef Timer_H
#define Timer_H

namespace byhj
{
	class Timer
	{
	public:
		Timer();
		~Timer();


		void Reset();
		void Start();
		void Stop();
		void Count();

		float GetTotalTime() const;
		float GetDeltaTime() const;

	private:
		
	};
}

#endif
