import styles from "../page.module.css"

export default function Footer() {
  let year = new Date().getFullYear();

  return (
    <footer className={styles.footer}>
      <span>NLP Platform</span>
      <span>&copy;{year} Michał Czyż, Dawid Głąb. All rights reserved.</span>
    </footer>
  );
}
