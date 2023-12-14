//Verifica Palindrono.
//solução 1
function verificaPalindrono(string) {
    if (!string) return "string inexistente";

    return string.split("").reverse().join("") === string;
}
console.log(verificaPalindrono("roma amor"));

//solução 2
function verificaPalindrono2(string) {
    if (!string) return "string inexistente";

    for (let i = 0; i < string.length; i++) {
        if (string[i] !== string[string.length - 1 - i] ) {
            return false;
        }
    }

    return true;
}

console.log(verificaPalindrono2("roma amor"));