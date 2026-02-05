// scripts/script.js

document.addEventListener("DOMContentLoaded", function () {

    const form = document.getElementById("loginForm");

    if (form) {
        form.addEventListener("submit", function (event) {
            event.preventDefault();

            // Get entered values
            const email = form.querySelector('input[type="email"]').value;
            const password = form.querySelector('input[type="password"]').value;

            alert(
                "⚠️ Phishing Simulation Result:\n\n" +
                "You entered:\n" +
                "Email: " + email + "\n" +
                "Password: " + password + "\n\n" +
                "This demonstrates how attackers capture credentials.\n" +
                "Never enter sensitive information on suspicious websites."
            );
        });
    }

});
