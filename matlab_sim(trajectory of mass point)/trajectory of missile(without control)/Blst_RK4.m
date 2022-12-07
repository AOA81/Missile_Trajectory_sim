
function RK4 = Blst_RK4(t, State, incre)

K1 = Blst_Dyna(t, State);   
K2 = Blst_Dyna(t + incre / 2, State + incre / 2 * K1);  
K3 = Blst_Dyna(t + incre / 2, State + incre / 2 * K2);  
K4 = Blst_Dyna(t + incre, State + incre * K3);  
RK4 = State + incre / 6 * (K1 + 2 * K2 + 2 * K3 + K4); 