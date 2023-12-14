const numberOfMatches = parseInt(gets());
let n = numberOfMatches;

let totalMatches = 0;

    while(n>1){
        if(n%2==0){
            totalMatches += n/2;
                n = n/2
        }else{
            totalMatches +=(n-1)/2;
                n = (n-1)/2+1
        }
    }
    console.log(totalMatches)

/*
var squads = 14;             //parseInt(gets())
var totalMatches = 0;
var sobra = 0;
var numberOfMatches = 0;

while (squads >= 2) {
    if (sobra == 1) {
        squads = squads + 1;
    }
    if (squads % 2 === 1) {
        numberOfMatches = (squads - 1) / 2;
        sobra = 1;
        squads = numberOfMatches;
    } else
        numberOfMatches = squads / 2;
     squads = numberOfMatches;

    totalMatches = totalMatches + numberOfMatches;

}
console.log(totalMatches); */






