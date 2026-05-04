#include <ntddk.h>

VOID PepperbootUnload(_In_ PDRIVER_OBJECT DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);
    DbgPrint("Pepperboot: Driver Unloaded\n");
}

VOID PepperbootWorkerThread(PVOID StartContext)
{
    UNREFERENCED_PARAMETER(StartContext);

    LARGE_INTEGER interval;
    interval.QuadPart = -10 * 1000 * 1000; 

    for (int i = 0; i < 5; i++)
    {
        DbgPrint("Pepperboot: Boot-stage execution tick %d\n", i);
        KeDelayExecutionThread(KernelMode, FALSE, &interval);
    }

    PsTerminateSystemThread(STATUS_SUCCESS);
}

// driver entry point
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    DbgPrint("Pepperboot: Boot driver loaded\n");

    DriverObject->DriverUnload = PepperbootUnload;

    HANDLE threadHandle;
    NTSTATUS status;

    // create system thread 
    status = PsCreateSystemThread(
        &threadHandle,
        THREAD_ALL_ACCESS,
        NULL,
        NULL,
        NULL,
        PepperbootWorkerThread,
        NULL
    );

    if (!NT_SUCCESS(status))
    {
        DbgPrint("Pepperboot: Failed to create thread\n");
        return status;
    }

    ZwClose(threadHandle);

    return STATUS_SUCCESS;
}
