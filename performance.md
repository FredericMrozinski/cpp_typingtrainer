# Performance analysis

## Findings

We used `gprof` to find potential efficiency leaks. However, we did not find any significant time-consuming computations. This aligns well with our previous assumptions: The TypingTrainer mainly performs I/O operations (file reading/writing and reading/writing from/to the terminal). All resulting events are processed in the statistical handlers by arithmetically modifying few variables and array values. Therefore, there we did not expect any heavy computation parts. 

Further, even though the TypingTrainer does run in real-time, the "computational repetion rate" is given by the users' typing speed, which is typically slow. We therefore spend most time waiting for the user's input. This time however does not count as computation time as the program is in an idle-state during the waiting time.

## Optimization applied

Firstly, the results described above do not require any heavy optimization. Therefore, even though at parts some computations might be minimally redundant, we do not shoot for fixing those for the sake of keeping code readability with barely any performance loss. We'd like to refer from the lecture where the key argument of optimization was: don't optimize unless it's necessary.

Nonetheless, we'd like to showcase some design choices and explain our thoughts w.r.t. optimization behind them:

- `std::map`s in `TypingStatsV2.cpp`: TypingStats is based heavily on `std::map`s for fast information retrieval. In contrast to arrays, retrieving values for certain keys does not require the knowledge of their memory positions. Therefore, we do not risk O(n) search operations. Instead, `std::map` provides key retrieving at O(log n). Find this technique also applied in `utils.cpp`. Unfortunately, relying heavily on maps required us to write custom code for map merging as we did not find convenient STL-functionality for this.
- Variable redundancy in `TypingStatsV2.h`: As elaborated on in `TypingStatsV2.h`, we introduced "redundant" variables that capture information that could be retrieved from other containers. However, this retrieval would require additional computation that we wanted to avoid by introducing extra variables at the cost of minor memory overhead. This is described in more detail in `TypingStatsV2.h`. This saved code and reduced predisposition for potential errors.
- Compiler flags: In our `CMakeLists.txt` we obviously ask for third level compiler optimization. Praise the compiler!

