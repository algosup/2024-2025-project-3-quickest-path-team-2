document.addEventListener("DOMContentLoaded", function() {
    window.onload = function() {
        setTimeout(() => {
            const loaderWrapper = document.querySelector(".loader-wrapper");
            if (loaderWrapper) {
                loaderWrapper.style.opacity = "0";
                setTimeout(() => loaderWrapper.style.display = "none", 500);
            }
        }, 1500);
    };
});

