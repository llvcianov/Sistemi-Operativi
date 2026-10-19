# Operating Systems

Lab exercises and exam practice for the **Operating Systems** course (Sistemi Operativi), Bachelor's Degree in Computer Engineering, University of Naples Federico II.

> **Note**: university coursework from 2020–2023, written for teaching purposes — concurrent/multiprocess programming in C on Linux (POSIX processes, threads, semaphores, message queues, shared memory, monitors). Not meant to reflect modern production practices. Assignment texts (PDFs) are in Italian, left as originally provided.

## Esercitazioni (Lab Exercises)

### [CodeMessaggi/](Esercitazioni/CodeMessaggi) — Message Queues
- **[2_prod_cons_async/](Esercitazioni/CodeMessaggi/2_prod_cons_async)** — producer/consumer over a SysV message queue, producer sending non-blocking (`IPC_NOWAIT`).
- **[Esercitazione_17-11-2022/](Esercitazioni/CodeMessaggi/Esercitazione_17-11-2022)** — multiprocess spooler: 5 Client processes send messages to a Server, which batches them to a Printer process (see its own [readme](Esercitazioni/CodeMessaggi/Esercitazione_17-11-2022/readme.md) and diagram for the full assignment).
- **[esercizio_code_sincrone/](Esercitazioni/CodeMessaggi/esercizio_code_sincrone)** — synchronous (rendezvous-style) message passing built on top of SysV queues, using a ready/ack handshake.

### [LettScritt/LettScrittStarvationScritt/](Esercitazioni/LettScritt/LettScrittStarvationScritt) — Readers-Writers
Classic two-semaphore readers-writers mutual exclusion over a shared-memory counter.

### [ProdCons/](Esercitazioni/ProdCons) — Producer-Consumer
- **[ProdConsBuffCircolare/](Esercitazioni/ProdCons/ProdConsBuffCircolare)** — multi-slot circular buffer, multiple producers/consumers.
- **[ProdConsBufferSingolo/](Esercitazioni/ProdCons/ProdConsBufferSingolo)** — single-slot buffer, one producer/one consumer.

### [Semafori/](Esercitazioni/Semafori) — Semaphore Fundamentals
Basic mutual exclusion over a shared counter incremented by two child processes, used to make a race condition visible without the lock.

## Esami (Past Exams & Self-Assessment)

### [Prove d'esame/](<Esami/Prove d'esame>)
- **[Compito-15-02-2021-con-soluzione/](<Esami/Prove d'esame/Compito-15-02-2021-con-soluzione>)** — monitor-based producer/consumer with a circular buffer and a timer thread; producers/consumer abandon waiting after a timeout.
- **[Compito-07-07-2011/](<Esami/Prove d'esame/Compito-07-07-2011>)** — monitor-based thread-safe stack (pthread mutex + condition variables): 5 producer threads pushing random values, 1 consumer thread popping and summing them.

### [ProveAutovalutazione/](Esami/ProveAutovalutazione)
- **[Autovalutazione_2/](Esami/ProveAutovalutazione/Autovalutazione_2)** — multiprocess pipeline (generators → mailbox → calculators → Hoare-monitor readers-writers → printers).
- **[Autovalutazione_1/](Esami/ProveAutovalutazione/Autovalutazione_1)** — multiprocess producer/consumer matched by key, shared buffer.

### [Tracce esame/](<Esami/Tracce esame>)
- **[Compito-10_21-12-20_consoluzione/](<Esami/Tracce esame/Compito-10_21-12-20_consoluzione>)** — Store/Viewer/Updater processes over message queues with per-product readers-writers; two independently written solutions ([`Soluzione/`](<Esami/Tracce esame/Compito-10_21-12-20_consoluzione/Soluzione>) and [`Soluzione_Alternativa/`](<Esami/Tracce esame/Compito-10_21-12-20_consoluzione/Soluzione_Alternativa>)).
- **[Compito-7_21-12-21_consoluzione/](<Esami/Tracce esame/Compito-7_21-12-21_consoluzione>)** — Client sensors feeding a Server with worker + collector threads averaging measurements; two independently written solutions ([`Soluzione/`](<Esami/Tracce esame/Compito-7_21-12-21_consoluzione/Soluzione>) and [`Soluzione_Alternativa/`](<Esami/Tracce esame/Compito-7_21-12-21_consoluzione/Soluzione_Alternativa>)).
- **[esame C - svolto/](<Esami/Tracce esame/esame C - svolto>)** — sensor/dispatcher readers-writers exercise over shared memory.
- **[esame_A - svolto/](<Esami/Tracce esame/esame_A - svolto>)** — producer/consumer with two message types sharing one buffer.
- **[esame_B/](<Esami/Tracce esame/esame_B>)** — generators → mailbox → filters → Hoare-monitor circular buffer → printers; two independently written solutions ([`Soluzione/`](<Esami/Tracce esame/esame_B/Soluzione>) and [`Soluzione_Alternativa/`](<Esami/Tracce esame/esame_B/Soluzione_Alternativa>)).

### [preappello/](Esami/preappello)
Pre-exam practice test (sensor/dispatcher readers-writers, same pattern as "esame C"): the originally distributed [`Scheletro_Soluzione/`](Esami/preappello/Scheletro_Soluzione) template paired with the completed [`Soluzione/`](Esami/preappello/Soluzione) submitted for it.

## Structure

```
Esercitazioni/
├── CodeMessaggi/
│   ├── 2_prod_cons_async/
│   ├── Esercitazione_17-11-2022/
│   └── esercizio_code_sincrone/
├── LettScritt/
│   └── LettScrittStarvationScritt/
├── ProdCons/
│   ├── ProdConsBuffCircolare/
│   └── ProdConsBufferSingolo/
└── Semafori/

Esami/
├── Prove d'esame/
│   ├── Compito-15-02-2021-con-soluzione/
│   │   └── Soluzione/
│   └── Compito-07-07-2011/
│       └── Soluzione/
├── ProveAutovalutazione/
│   ├── Autovalutazione_2/
│   │   └── Soluzione/
│   └── Autovalutazione_1/
│       └── Soluzione/
├── Tracce esame/
│   ├── Compito-10_21-12-20_consoluzione/   (Soluzione/ + Soluzione_Alternativa/)
│   ├── Compito-7_21-12-21_consoluzione/    (Soluzione/ + Soluzione_Alternativa/)
│   ├── esame C - svolto/
│   │   └── Soluzione/
│   ├── esame_A - svolto/
│   │   └── Soluzione/
│   └── esame_B/                            (Soluzione/ + Soluzione_Alternativa/)
└── preappello/
    ├── Soluzione/
    └── Scheletro_Soluzione/
```

Within each exam folder, the assignment PDF sits alongside a `Soluzione/` (and, where a second independent attempt or the originally distributed skeleton exists, `Soluzione_Alternativa/` / `Scheletro_Soluzione/`).

Not containerized — reference code, built with the included Makefiles on Linux with gcc.
