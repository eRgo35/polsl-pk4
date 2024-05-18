"use client"
import styles from "../page.module.css"
import Link from 'next/link'
import { usePathname } from 'next/navigation'

export default function SideBar() {
  let userStatus = "Sign in";
  
  const pathname = usePathname()

  return (
  <nav className="sidebar offcanvas-start offcanvas-md" tabIndex="-1" id="sidebar-example">
    <div className="offcanvas-header">
      <a className="sidebar-brand" href="/">
        NLP Platform
      </a>
      <button type="button" className="btn-close d-md-none" data-bs-dismiss="offcanvas" aria-label="Close" data-bs-target="#sidebar-example"></button>
    </div>
    <div className="offcanvas-body">
    {/*
      <div className="mt-2 mb-3">
        <input type="text" className="form-control" placeholder="Search" />
      </div>
    */}
      <ul className="sidebar-nav">
        <li>
          <h6 className="sidebar-header">Text Analysis</h6>
        </li>
        <li><hr className="sidebar-divider" /></li>
        <li className="nav-item">
          <Link className={pathname == "/sentiment" ? "active nav-link" : "nav-link"} href="/sentiment">Sentiment Analysis</Link>
        </li>
        <li className="nav-item">
          <Link className={pathname == "/translate" ? "active nav-link" : "nav-link"} href="/translate">Machine Translation</Link>
        </li>
        <li className="mt-3">
          <h6 className="sidebar-header">Settings</h6>
        </li>
        <li><hr className="sidebar-divider" /></li>
        <li className="nav-item">
          <Link className={pathname == "/preferences" ? "active nav-link" : "nav-link"} href="/preferences">Preferences</Link>
        </li>
        <li className="nav-item">
          <Link className={pathname == "/signin" ? "active nav-link" : "nav-link"} href="/signin">{ userStatus }</Link>
        </li>
      </ul>
    </div>
  </nav>
  );
}
