## Mitigating bias in Boolean circuits

This experiment is divided into two parts, studying a particular case of a circuit called
“Alternate circuits” by requiring that x1 ∧ x2 always appears at the
first level, while x3 ∧ x4 never appears, and all circuits have a size limit of 50 gates.

- In the first part, we observe what happens when we enforce that x1 ∧ x2 only
affects one branch of the circuit. The goal is to find functions that are able to be
equanimous at least between {x1, x2} and {x3, x4}, i.e., to find functions that have
a similar behavior to PARITY.

- On the other hand, if we “poison” the entire second level with the output of gate
x1∧x2, then it is impossible for the function not to be biased in favor of x1∧x2. This
supports the conjecture that a function computed by a small and tangled circuit
cannot be equanimous.

#### Link to the data

https://drive.google.com/drive/folders/1AMncGc78D34tQB6WdM84OUsLg9uEvU2b?usp=share_link