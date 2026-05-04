# Pepperboot

Pepperboot is a boot-time system framework designed to ensure that administrative software starts extremely early in the Windows boot process and remains reliably active with high privilege throughout system operation.

It is intended to combine a boot-start kernel driver and SYSTEM-level service layer to enforce early execution and resistance to interruption.

---

## What Pepperboot does (functionally)

At a practical level, Pepperboot spawns a proccess really early in the windows boot proccess and ensures it keeps running.

---

WARNING: Pepperboot is in early development and is not stable. DO NOT deploy this to a fleet of computers unless you know what you're doing. Installing pepperboot on someone's computer without their explitit educated consent is an illegal cybercrime. I am not responsible for how you use this program.
