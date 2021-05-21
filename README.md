# YuyuanCup

## Introdution
Yuyuan Cup is a game to build self-conrtolled car to finish given tasks to reach the highest score, which are hosted by BUAA ASEE. In Yuyuan Cup 2020~2021, the self driving cars were asked to 
- touch the light house with given color
- hit the adverarial car's back traking light
- going back starting spot when the game is over

## Structure 
- The contolling logic of car are implmented in `arduino/` with arduino DUE. 
- we apply openMV packed color-detection algorithm to track the light with given color.
- the coder&motor-control and PID algorithm for motors are packed in `lib/CoderMotor`  

## Appendix：
[比赛规则](https://bhpan.buaa.edu.cn/#/link/7E5CFF6D305448837059D5E1C2D75403)
    
