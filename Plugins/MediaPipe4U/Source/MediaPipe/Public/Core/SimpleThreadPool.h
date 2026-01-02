// Copyright (c) 2025 Anders Xiao. All rights reserved.
// https://github.com/endink

#pragma once

#include "CoreMinimal.h"
#include "Misc/IQueuedWork.h"
#include "Misc/QueuedThreadPool.h"
#include "Misc/EngineVersionComparison.h"

class FSimpleQueuedThread;

class MEDIAPIPE_API FSimpleThreadPool
{
protected:

	/** The work queue to pull from. */
	FThreadPoolPriorityQueue QueuedWork;
	TSet<TSharedPtr<IQueuedWork>> AllWorks;
	
	/** The thread pool to dole work out to. */
	TArray<FSimpleQueuedThread*> QueuedThreads;

	/** All threads in the pool. */
	TArray<FSimpleQueuedThread*> AllThreads;

	/** The synchronization object used to protect access to the queued work. */
	FCriticalSection* SynchQueue;

	/** If true, indicates the destruction process has taken place. */
	bool TimeToDie;

public:

	/** Default constructor. */
	FSimpleThreadPool()
		: SynchQueue(nullptr)
		, TimeToDie(0)
	{ }

	/** Virtual destructor (cleans up the synchronization objects). */
	virtual ~FSimpleThreadPool();

	virtual bool Create(uint32 InNumQueuedThreads, uint32 StackSize, EThreadPriority ThreadPriority, const TCHAR* Name);

	virtual bool CreateForkable(uint32 InNumQueuedThreads, uint32 StackSize, EThreadPriority ThreadPriority, const TCHAR* Name);

	void Destroy();

	void CancelAll();

	int32 GetNumQueuedJobs() const;

	int32 GetNumThreads() const;
 
	virtual void AddQueuedWork(const TSharedPtr<IQueuedWork>& InQueuedWork, EQueuedWorkPriority InQueuedWorkPriority = EQueuedWorkPriority::Normal);

	virtual bool RetractQueuedWork(const TSharedPtr<IQueuedWork>& InQueuedWork);

private:
	IQueuedWork* ReturnToPoolOrGetNextJob(FSimpleQueuedThread* InQueuedThread, IQueuedWork* DoneWork);
	bool CreateInternal(bool bForkable, uint32 InNumQueuedThreads, uint32 StackSize, EThreadPriority ThreadPriority, const TCHAR* Name);

	friend class FSimpleQueuedThread;
};
