import styles from "../page.module.css"

export default function Footer() {
  let year = new Date().getFullYear();

  return (
    <footer>
      <span>Copyright &copy;{year} Michał Czyż, Dawid Głąb</span>
      <span>All rights reservered.</span>
    </footer>
  );
}
