import styles from "../page.module.css"

export default function Content() {
  return (
    <div className={styles.content}>
      <div className={styles.mainui}>Main content window.</div>
      <div className={styles.sender}>
      <input /><button>Send</button>
      </div>
    </div>
  );
}
