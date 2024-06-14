/** @type {import('tailwindcss').Config} */
/*eslint-env node*/
module.exports = {
  content: ["./src/**/*.{html,js,jsx}"],
  theme: {
    extend: {
      fontFamily:{
        playfair:"'Playfair Display',serif",
        lato:"'Lato',sans-serif",
      }
    },
  },
  plugins: [],
}