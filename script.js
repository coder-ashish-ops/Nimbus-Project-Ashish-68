/* ----------- CALCULATE EMI ----------- */
function calculate() {
    let loan = parseFloat(document.getElementById("loan").value);
    let rate = parseFloat(document.getElementById("rate").value) / 12 / 100;
    let years = parseFloat(document.getElementById("years").value) * 12;
    let income = parseFloat(document.getElementById("income").value);

    if(!loan || !rate || !years || !income){
        alert("Please fill all fields!");
        return;
    }

    let emi = (loan * rate * Math.pow(1 + rate, years)) /
              (Math.pow(1 + rate, years) - 1);

    emi = emi.toFixed(2);

    let total = (emi * years).toFixed(2);
    let interest = (total - loan).toFixed(2);

    let eligible = emi <= income * 0.40 ? "YES" : "NO";

    let affordability =
        emi <= income * 0.25 ? "Excellent" :
        emi <= income * 0.40 ? "Good" :
        emi <= income * 0.60 ? "Risky" : "Very Risky";

    // Show Result Page
    document.getElementById("mainPage").style.display = "none";
    document.getElementById("resultPage").style.display = "block";

    document.getElementById("r_emi").innerText = emi;
    document.getElementById("r_interest").innerText = interest;
    document.getElementById("r_total").innerText = total;
    document.getElementById("r_eligible").innerText = eligible;
    document.getElementById("r_afford").innerText = affordability;
}

/* ----------- GO BACK ----------- */
function goBack() {
    document.getElementById("mainPage").style.display = "block";
    document.getElementById("resultPage").style.display = "none";
}

/* ----------- THEME CHANGER ----------- */
function setTheme(mode){
    document.body.classList.remove("dark","blue");

    if(mode === "dark") document.body.classList.add("dark");
    if(mode === "blue") document.body.classList.add("blue");

    localStorage.setItem("theme", mode);
}

/* Load saved theme */
window.onload = () => {
    let saved = localStorage.getItem("theme");
    if(saved) setTheme(saved);
};
