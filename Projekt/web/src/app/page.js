import styles from "./page.module.css";

import Header from "./components/Header";
import SideBar from "./components/SideBar";
import Content from "./components/Content";
import Footer from "./components/Footer";

export default function Home() {
  return (
    <main className={styles.main}>
      <Header />
      <div className={styles.mainframe}>
        <SideBar />
        <Content />
      </div>
      <Footer />
    </main>
  );
}
