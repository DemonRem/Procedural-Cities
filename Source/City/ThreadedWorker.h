// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HouseBuilder.h"

class AHouseBuilder;
//~~~~~ Multi Threading ~~~
class ThreadedWorker : public FRunnable
{
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  ThreadedWorker* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	AHouseBuilder *houseBuilder;
	FHousePolygon housePol;
	float floorHeight;
	float maxRoomArea;
	bool shellOnly;
	bool simple;
	/** The PC */
	//AVictoryGamePlayerController* ThePC;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

private:
	int32				PrimesFoundCount;
public:
	FHouseInfo resultingInfo;
	bool fullReplacement;
	bool done = false;

	//Done?
	bool IsFinished() const
	{
		return done;
	}

	//~~~ Thread Core Functions ~~~

	//Constructor / Destructor
	ThreadedWorker(AHouseBuilder *house, FHousePolygon p, float floorHeight, float maxRoomArea, bool shellOnly, bool simple, bool fullReplacement);
	virtual ~ThreadedWorker();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();



	//~~~ Starting and Stopping Thread ~~~



	//static ThreadedWorker* JoyInit(AHouseBuilder *house, FHousePolygon p, float floorHeight, float maxRoomArea, bool shellOnly, bool simple, bool fullReplacement);

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();

};