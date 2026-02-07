/* templates/landing-pages/fake-login-page/script.js */

document.addEventListener("DOMContentLoaded", function () {

  const form = document.querySelector("form");

  form.addEventListener("submit", function (e) {
    e.preventDefault();

    const email = form.querySelector("input[name='email']").value;
    const password = form.querySelector("input[name='password']").value;

    console.log("Simulation Input Captured:", {
      email: email,
      password: password
    });

    // Educational simulation only — no real credential storage
    alert("Simulation complete. This was part of a phishing awareness exercise.");

    window.location.href = "../awareness-redirect-page/index.html";
  });

});
